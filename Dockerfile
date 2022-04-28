FROM gcc:11.3.0

WORKDIR /usr/src/app

RUN apt-get -qq update && \
    apt-get install -y libgtest-dev && \
    rm -rf /var/lib/apt/lists/*

COPY . .

RUN make

CMD [ "build/example_rainflow", "example/samples.txt" ]