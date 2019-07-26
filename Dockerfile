FROM danoan/min-env:1.boost-filesystem

RUN apt-get install lcov -y

WORKDIR /magLac
ADD . /magLac

RUN chmod u+x /magLac/.travis/*
RUN mkdir /magLac/build-release && mkdir /magLac/install

RUN /magLac/.travis/build-magLac.sh \
/magLac \
/magLac/build-release \
/magLac/install \
Release \
OFF

RUN /magLac/.travis/build-magLac.sh \
/magLac \
/magLac/build-debug \
/magLac/install-debug \
Debug \
ON


