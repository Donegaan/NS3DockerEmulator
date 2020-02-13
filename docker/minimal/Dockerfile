############################################################
# Build stage
############################################################

FROM golang:1.9 as builder

# Building Beacon simple app
WORKDIR /go/src/github.com/Donegaan
RUN git clone https://github.com/Donegaan/Beacon.git
WORKDIR /go/src/github.com/Donegaan/Beacon
RUN go get && CGO_ENABLED=0 go install -a -tags netgo -ldflags '-extldflags "-static"'

RUN ldd /go/bin/Beacon | grep -q "not a dynamic executable"

# FROM ubuntu as multichain-builder

# ENV DEBIAN_FRONTEND noninteractive
# ENV LANG en_US.UTF-8
# ENV LC_ALL C.UTF-8

# WORKDIR /root/.multichain
############################################################
# Run stage
############################################################

FROM alpine

#RUN apk update && apk add bash

COPY wrapper.sh /wrapper.sh
RUN chmod +x /wrapper.sh
COPY --from=builder /go/bin/Beacon /beacon

ENV MULTICHAIN_VERSION 2.0.5

WORKDIR /tmp

RUN apk update \
  && apk upgrade -q \
  # && apk dist-upgrade -q \
  && apk add -q wget curl python \
  # && apk clean \
  && rm -rf /var/lib/apt/lists/* \
  && wget -nv https://www.multichain.com/download/multichain-${MULTICHAIN_VERSION}.tar.gz \
  && tar -xvzf multichain-${MULTICHAIN_VERSION}.tar.gz \
  && cd multichain-${MULTICHAIN_VERSION} \
  && mv multichaind multichain-cli multichain-util /usr/local/bin \
  && curl https://bootstrap.pypa.io/get-pip.py | python \
  && pip install dump-env -q \
  && mkdir /root/.multichain \
  && rm -rf /tmp/multichain-${MULTICHAIN_VERSION}

COPY *.template /root/.multichain/
# COPY --from=multichain-builder /tmp /tmp

#CMD ["bash", "/wrapper.sh"]
CMD /wrapper.sh

# docker build -t hello-world-multi-stage .
# docker run hello-world-multi-stage
# docker image ls hello-world-multi-stage