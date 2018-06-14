Name: iotjs
Version: 1.0
Release: 0
Summary: Platform for Internet of Things with JavaScript
Source: %{name}-%{version}.tar.gz
Group: Network & Connectivity
License: Apache-2.0
URL: https://iotjs.net/
#X-Vcs-Url: https://github.com/Samsung/iotjs/

%ifarch armv7l armv7hl armv7nhl armv7tnhl armv7thl
%define arch_type arm
%define TARGET_BOARD artik10
%endif

%{!?arch_type: %define arch_type %{_arch}}
%{!?os_type: %define os_type tizen}
%{!?prefix: %define prefix /usr}

BuildRequires: cmake
BuildRequires: make
BuildRequires: python


%description
Platform for Internet of Things with JavaScript


%prep
%setup -q -n %{name}-%{version}

#touch deps/libtuv/cmake/config/config_%{arch_type}-%{os_type}.cmake
#touch deps/libtuv/cmake/option/option_%{arch_type}-%{os_type}.cmake

 #ln -fs  \
 #es5.1.profile \
 #deps/jerry/jerry-core/profiles/.profile

#  -DCMAKE_C_COMPILER="gcc"
#  -DCMAKE_SYSTEM_PROCESSOR="%{arch_type}"
#  -DCMAKE_SYSTEM_NAME="Linux"
# -DTARGET_BOARD="%{TARGET_BOARD}" 

%build
CMAKE_OPTIONS='-DFEATURE_PROFILE=es5.1  -DPLATFORM_DESCRIPTOR=noarch-linux  -DCMAKE_INSTALL_PREFIX="%{prefix}"'
export CMAKE_OPTIONS

which cc
cc --version
cmake .
cmake --build . || make V=1 VERBOSE=1

%install
%make_install


%clean


%files
%license LICENSE
/usr/*
