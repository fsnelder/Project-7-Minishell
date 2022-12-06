FROM ubuntu:20.04
RUN apt-get update \
  && apt-get install -y ssh \
      gcc \
      g++ \
      gdb \
      cmake \
      valgrind \
      libreadline-dev \
    && apt-get clean
RUN mkdir /app
ENTRYPOINT ["tail", "-f", "/dev/null"]
