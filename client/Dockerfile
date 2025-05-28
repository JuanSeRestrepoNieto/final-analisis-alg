FROM ubuntu:22.04

ENV http_proxy=""
ENV https_proxy=""
ENV HTTP_PROXY=""
ENV HTTPS_PROXY=""

RUN apt update && apt install -y g++ libssl-dev

COPY aes_utils.h /aes_utils.h
COPY client.cpp /client.cpp

RUN g++ /client.cpp -o /client -lssl -lcrypto

CMD ["./client"]
