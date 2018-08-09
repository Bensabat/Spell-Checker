FROM ubuntu:17.10

RUN apt-get update \
    && apt-get install -y gcc g++ clang-4.0 libomp-dev cmake valgrind \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
