FROM alpine:3.19
WORKDIR /app
RUN apk add --no-cache g++ make
COPY *.cpp Makefile ./
RUN make
CMD ["./labo1"]