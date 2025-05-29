# Etapa 1: compilación
FROM alpine:3.18 AS builder

RUN apk add --no-cache g++ build-base openssl-dev

WORKDIR /app
COPY client.cpp .
COPY totp_aes_utils.h .

RUN g++ client.cpp -o client -lssl -lcrypto

# Etapa 2: imagen final mínima
FROM alpine:3.18

RUN apk add --no-cache libstdc++ libgcc

WORKDIR /app
COPY --from=builder /app/client .

CMD ["./client"]
