FROM ubuntu:22.04

ENV http_proxy=""
ENV https_proxy=""
ENV HTTP_PROXY=""
ENV HTTPS_PROXY=""

RUN apt update && apt install -y g++ libssl-dev

COPY server.cpp /server.cpp
COPY aes_utils.h /aes_utils.h

RUN g++ server.cpp -o server -lssl -lcrypto

CMD ["./server"]
