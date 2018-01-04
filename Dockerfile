#!/bin/echo docker build . -f
#!/bin/echo docker run --rm -v /usr/bin/qemu-arm-static:/usr/bin/qemu-arm-static -ti bash
# -*- coding: utf-8 -*-

#FROM philipz/rpi-raspbian
#FROM debian:stable
FROM resin/armv7hf-debian
RUN [ "cross-build-start" ]


MAINTAINER Philippe Coval (philippe.coval@osg.samsung.com)

ENV DEBIAN_FRONTEND noninteractive
ENV LC_ALL en_US.UTF-8
ENV LANG ${LC_ALL}

RUN echo "#log: Configuring locales" \
 && apt-get update \
 && apt-get upgrade \
 && apt-get install -y locales \
 && echo "${LC_ALL} UTF-8" | tee /etc/locale.gen \
 && locale-gen ${LC_ALL} \
 && dpkg-reconfigure locales

ENV project iotjs

RUN echo "#log: Preparing system for ${project}" \
 && apt-get update -y \
 && apt-get install -y \
  bash \
  git \
  make \
  sudo \
  gawk \
 && apt-get clean \
 && sync

ADD . /usr/local/src/${project}
WORKDIR /usr/local/src/${project}
RUN echo "#log: Building ${project}" \
 && ./debian/rules rule/setup \
 && sync

RUN echo "#log: Building ${project}" \
 && ./debian/rules \
 && sudo debi \
 && dpkg -L ${project} \
 && sync

RUN [ "cross-build-end" ]  
