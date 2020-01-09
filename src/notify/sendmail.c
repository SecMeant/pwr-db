#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

#define SMTP_SERVER "smtp://smtp.gmail.com"

#define USERNAME "biuro_podrozy"
#define PASSWORD "supersecret"

const char FROM_TEMPLATE[] = "From: %s\r\n";
const char TO_TEMPLATE[]   = "To: %s\r\n";

const char REMIND_MSG[] = "Remind about tour\r\n";
const char ALERT_MSG[]  = "Alert about tour\r\n";

static const char *payload_text[] = {
  "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
  "To: \r\n",   // Will be overwritten later
  "From: \r\n", // Will be overwritten later
  "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
  "rfcpedant.example.org>\r\n",
  "Subject: SMTP SSL example message\r\n",
  "\r\n", /* empty line to divide headers from body, see RFC5322 */
  "The body of the message.\r\n", // Will be overwritten
  "\r\n",
  NULL
};

struct upload_status {
  int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;

  if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }

  data = payload_text[upload_ctx->lines_read];

  if(data) {
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read++;

    return len;
  }

  return 0;
}

// Takes 3 arguments:
// argv[1] == Recipent (To) address
// argv[2] == Sender (From) address
// argv[3] == body of the message
int main(int argc, char **argv)
{
  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  struct upload_status upload_ctx;

  if (argc != 4)
    return -1;

  const char * to   = argv[1];
  const char * from = argv[2];
  payload_text[7]   = argv[3];

  char * to_line   = (char *) malloc(strlen(to)   + sizeof(TO_TEMPLATE));
  char * from_line = (char *) malloc(strlen(from) + sizeof(FROM_TEMPLATE));

  if (sprintf(to_line  , TO_TEMPLATE  , from) < 0) {
    res = -2;
    goto exit;
  }

  if (sprintf(from_line, FROM_TEMPLATE, from) < 0) {
    res = -2;
    goto exit;
  }

  payload_text[1] = to_line;
  payload_text[2] = from_line;
  payload_text[7] = REMIND_MSG;
  payload_text[8] = argv[4];

  upload_ctx.lines_read = 0;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_USERNAME, USERNAME);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, PASSWORD);

    curl_easy_setopt(curl, CURLOPT_URL, SMTP_SERVER);

#ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from);

    recipients = curl_slist_append(recipients, to);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    curl_slist_free_all(recipients);

    curl_easy_cleanup(curl);
  }

exit:
  free(to_line);
  free(from_line);
  return (int)res;
}
