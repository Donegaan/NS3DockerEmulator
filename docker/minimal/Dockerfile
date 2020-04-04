FROM golang:1.9 as builder

# Building Beacon simple app
RUN git clone https://github.com/Donegaan/Beacon.git
RUN cd Beacon
RUN go get && CGO_ENABLED=0 go install -a -tags netgo -ldflags '-extldflags "-static"'

RUN ldd /go/bin/Beacon | grep -q "not a dynamic executable"

FROM alpine

# LABEL vendor="Chainstack"

# ENV DEBIAN_FRONTEND noninteractive
# ENV LANG en_US.UTF-8
# ENV LC_ALL C.UTF-8

ENV MULTICHAIN_VERSION 2.0.5

RUN apk update \
    && apk upgrade -q \
    && apk add -q wget curl nmap bash \
    && rm -rf /var/lib/apt/lists/* \
    && cd /tmp \
    && wget -nv https://www.multichain.com/download/multichain-${MULTICHAIN_VERSION}.tar.gz \
    && tar -xvzf multichain-${MULTICHAIN_VERSION}.tar.gz \
    && cd multichain-${MULTICHAIN_VERSION} \
    && mv multichaind multichain-cli multichain-util /usr/local/bin \
    && mkdir /root/.multichain \
    && cd /tmp \
    && rm -Rf multichain*

RUN echo "**** install Python ****" && \
    apk add python3 && \
    if [ ! -e /usr/bin/python ]; then ln -sf python3 /usr/bin/python ; fi && \
    \
    echo "**** install pip ****" && \
    python3 -m ensurepip && \
    rm -r /usr/lib/python*/ensurepip && \
    pip3 install --upgrade pip && \
    if [ ! -e /usr/bin/pip ]; then ln -s pip3 /usr/bin/pip ; fi

RUN pip3 install mcrpc

COPY create_blockchain.sh create_blockchain.sh
COPY start_blockchain.sh start_blockchain.sh
COPY connect_to_blockchain.sh connect_to_blockchain.sh
COPY publish_objects.py publish_objects.py

RUN chmod a+x create_blockchain.sh start_blockchain.sh connect_to_blockchain.sh

RUN ./create_blockchain.sh
RUN ./start_blockchain.sh

COPY wrapper.sh /wrapper.sh
RUN chmod +x /wrapper.sh
COPY --from=builder /go/bin/Beacon /beacon

# CMD ["/bin/bash"]
CMD /wrapper.sh

# CMD ["/bin/bash", "/root/create_blockchain.sh"]