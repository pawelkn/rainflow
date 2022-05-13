FROM ubuntu:latest

WORKDIR /usr/src/app

RUN apt-get update; \
    apt-get install -y --no-install-recommends make g++ libgtest-dev; \
    rm -rf /var/lib/apt/lists/*

COPY . .

RUN make

CMD [ "build/example_rainflow", "example/samples.txt" ]