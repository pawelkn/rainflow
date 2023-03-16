FROM ubuntu:latest

WORKDIR /usr/src/app

RUN apt-get update; \
    apt-get install -y --no-install-recommends make g++ libgtest-dev cmake; \
    rm -rf /var/lib/apt/lists/*

COPY . .

RUN cmake -S . -B build; \
    cmake --build build

CMD [ "build/example_rainflow", "example/samples.txt" ]