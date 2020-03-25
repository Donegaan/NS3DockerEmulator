FROM alpine

# LABEL vendor="Chainstack"

# ENV DEBIAN_FRONTEND noninteractive
# ENV LANG en_US.UTF-8
# ENV LC_ALL C.UTF-8

ENV MULTICHAIN_VERSION 2.0.5

RUN apk update \
    && apk upgrade -q \
    && apk add -q wget curl python3 nmap bash python3-pip \
    && pip3 install --upgrade pip3 \
    && pip3 install savoir \
    && rm -rf /var/lib/apt/lists/* \
    && cd /tmp \
    && wget -nv https://www.multichain.com/download/multichain-${MULTICHAIN_VERSION}.tar.gz \
    && tar -xvzf multichain-${MULTICHAIN_VERSION}.tar.gz \
    && cd multichain-${MULTICHAIN_VERSION} \
    && mv multichaind multichain-cli multichain-util /usr/local/bin \
    && mkdir /root/.multichain \
    && cd /tmp \
    && rm -Rf multichain*

COPY create_blockchain.sh create_blockchain.sh
COPY test.py test.py

RUN chmod a+x create_blockchain.sh

# RUN ./create_blockchain.sh

CMD ["/bin/bash"]

# CMD ["/bin/bash", "/root/create_blockchain.sh"]