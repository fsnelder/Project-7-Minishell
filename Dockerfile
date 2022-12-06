FROM ubuntu:20.04
RUN apt-get update \
  && apt-get install -y ssh \
      build-essential \
      gcc \
      g++ \
      gdb \
      clang \
      cmake \
      python \
      iputils-ping \
      git \
    && apt-get clean
