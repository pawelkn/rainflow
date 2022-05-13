FROM ubuntu:latest

WORKDIR /usr/src/app

RUN apt-get -qq update && \
    apt-get install -y build-essential libgtest-dev && \
    rm -rf /var/lib/apt/lists/*

COPY . .

RUN make

CMD [ "build/example_rainflow", "example/samples.txt" ]