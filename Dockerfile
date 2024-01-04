FROM alpine:3.19.0

WORKDIR /app

RUN apk update && \
    apk add --no-cache build-base cmake gtest-dev

COPY . .

RUN cmake -S . -B build; \
    cmake --build build

CMD [ "build/example_rainflow", "example/samples.txt" ]