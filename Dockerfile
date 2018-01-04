#!/bin/echo docker build . -f
# -*- coding: utf-8 -*-
#
# Copyright 2017 Samsung Electronics France SAS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

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
 && dpkg-reconfigure locales \
 && sync

ENV project iotjs

RUN echo "#log: Preparing system for ${project}" \
 && apt-get update -y \
 && apt-get install -y \
  make \
  sudo \
  gawk \
 && apt-get install -y \
  build-essential \
  devscripts \
  debhelper \
  fakeroot \
  cmake \
  git \
  python \
 && apt-get clean \
 && sync

ADD . /usr/local/src/${project}
WORKDIR /usr/local/src/${project}
RUN echo "#log: Setup system for ${project}" \
 && cat /etc/os-release \
 && ./debian/rules rule/setup \
 && sync

RUN echo "#log: Building ${project}" \
 && ./debian/rules \
 && sudo debi \
 && ls -la /usr/local/src/${project}*.* \
 && dpkg -L ${project} \
 && sync
