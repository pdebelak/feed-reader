#include "fetcher.h"

feed_type extract_feed_url(htmlNodePtr a_node, char **u) {
  htmlNodePtr cur_node = NULL;
  char *url = NULL;
  feed_type ft;

  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if (url != NULL) break;
    if (cur_node->type == XML_ELEMENT_NODE && xmlStrcmp(cur_node->name, (xmlChar *) "link") == 0) {
      xmlChar *type = xmlGetProp(cur_node, (const xmlChar *) "type");
      int is_atom = xmlStrcmp(type, (const xmlChar *) "application/atom+xml") == 0;
      int is_rss = xmlStrcmp(type, (const xmlChar *) "application/rss+xml") == 0;
      if (is_atom || is_rss) {
        if (is_atom) ft = ATOM;
        if (is_rss) ft = RSS;
        xmlChar *href = xmlGetProp(cur_node, (const xmlChar *) "href");
        url = strdup((char *)href);
        xmlFree(href);
      }
      xmlFree(type);
    }

    if (url == NULL) {
      ft = extract_feed_url(cur_node->children, &url);
    }
  }
  *u = url;
  return ft;
}

site * qualify_feed_urls(char *feed, char *url) {
  int feed_len = strlen(feed);
  int url_len = strlen(url);
  char * qualified_url;
  qualified_url = (char*) malloc(sizeof(char) * (feed_len + url_len + 1));
  int i = 0;
  for (; i < 8; i++) {
    qualified_url[i] = url[i];
  }
  while (url[i] != '/' && i < url_len) {
    qualified_url[i] = url[i];
    i++;
  }
  qualified_url[i] = '\0';
  site *s = NULL;
  s = malloc(sizeof(site));
  if (feed_len > 4 && feed[0] == 'h' && feed[1] == 't' && feed[2] == 't' && feed[3] == 'p') {
    s->base_url = qualified_url;
    s->feed_url = strdup(feed);
  } else {
    char *root_url = strdup(qualified_url);
    for (int j = 0; j < feed_len; j++) {
      qualified_url[i] = feed[j];
      i++;
    }
    qualified_url[i] = '\0';
    s->base_url = root_url;
    s->feed_url = qualified_url;
  }
  int max;
  max = strlen(s->base_url);
  for (i = 0; i < max; i++) {
    s->base_url[i] = tolower(s->base_url[i]);
  }
  max = strlen(s->feed_url);
  for (i = 0; i < max; i++) {
    s->feed_url[i] = tolower(s->feed_url[i]);
  }
  return s;
}

site * fetch_feed_url(char *url) {
  start_http();
  http_response *resp;
  int err = http_get_url(url, &resp);
  if (err != 0) {
    free_http_response(resp);
    stop_http();
    return NULL;
  }
  char *body;
  err = read_http_response_body(resp, &body);
  if (err != 0) {
    free_http_response(resp);
    stop_http();
    return NULL;
  }
  stop_http();

  htmlDocPtr page = htmlReadDoc((const xmlChar *) body, NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
  htmlNodePtr cur = xmlDocGetRootElement(page)->children;
  char *feed_url;
  feed_type ft = extract_feed_url(cur, &feed_url);
  xmlFreeDoc(page);
  xmlCleanupParser();
  if (feed_url == NULL) return NULL;
  site *s = qualify_feed_urls(feed_url, resp->url);
  s->type = ft;
  free_http_response(resp);
  free(feed_url);
  return s;
}
