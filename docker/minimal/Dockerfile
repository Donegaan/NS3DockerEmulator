FROM alpine

# LABEL vendor="Chainstack"

# ENV DEBIAN_FRONTEND noninteractive
# ENV LANG en_US.UTF-8
# ENV LC_ALL C.UTF-8

ENV MULTICHAIN_VERSION 2.0.5

WORKDIR /tmp

RUN apk update \
    && apk upgrade -q \
    # && apk dist-upgrade -q -y \
    && apk add -q wget curl python nmap bash \
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

COPY create_blockchain.sh create_blockchain.sh

RUN chmod +x create_blockchain.sh

RUN ./create_blockchain.sh

# CMD ["/bin/bash"]