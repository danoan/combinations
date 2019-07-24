FROM min-env:1.boost-filesystem

WORKDIR /magLac
ADD . /magLac

RUN chmod u+x /magLac/.travis/*
RUN mkdir /magLac/build-release && mkdir /magLac/install

RUN /magLac/.travis/build-magLac.sh \
/magLac \
/magLac/build-release \
/magLac/install \
release



