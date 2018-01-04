#!/bin/echo docker build . --rm -v /usr/bin/qemu-arm-static:/usr/bin/qemu-arm-static
#!/bin/echo docker build . -f
# -*- coding: utf-8 -*-

#FROM philipz/rpi-raspbian
FROM debian:stable
MAINTAINER Philippe Coval (philippe.coval@osg.samsung.com)

ENV DEBIAN_FRONTEND noninteractive
ENV LC_ALL en_US.UTF-8
ENV LANG ${LC_ALL}

RUN echo "#log: Configuring locales" \
 && apt-get update \
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
 && apt-get clean \
 && sync

ADD . /usr/local/src/${project}
WORKDIR /usr/local/src/${project}
RUN echo "#log: Building ${project}" \
 && ./debian/rules \
 && sync