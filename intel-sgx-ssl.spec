%define         openssl_version 1.1.1g
Name:           intel-sgx-ssl
Version:        2.10
Release:        1
Summary:        Intel® Software Guard Extensions SSL
License:        OpenSSL and BSD 3-clause "New" or "Revised" License
URL:            https://github.com/intel/intel-sgx-ssl
Source0:        https://github.com/intel/intel-sgx-ssl/archive/lin_%{version}_%{openssl_version}.zip
Source1:        https://www.openssl.org/source/old/1.1.1/openssl-%{openssl_version}.tar.gz

BuildRequires:  gcc 
BuildRequires:	libsgx-launch libsgx-urts linux-sgx-sdk

Requires:       glibc

%description
The Intel® Software Guard Extensions SSL (Intel® SGX SSL) cryptographic
library is intended to provide cryptographic services for
Intel® Software Guard Extensions (SGX) enclave applications.
The Intel® SGX SSL cryptographic library is based on the underlying
OpenSSL* Open Source project, providing a full-strength general purpose
cryptography library. Supported OpenSSL version is 1.1.1g.


%package devel
Summary:        Development files for intel sgx ssl
Requires:       %{name} = %{version}-%{release}

%description devel
%{summary}.


%package_help
%define debug_package %{nil}

%prep

%setup -q -n intel-sgx-ssl-lin_2.10_1.1.1g
%build
cp %{SOURCE1} openssl_source/
cd Linux
make sgxssl_no_mitigation

%install
cd Linux
make install DESTDIR=$RPM_BUILD_ROOT/opt/intel/sgxssl
cp -r package/docs $RPM_BUILD_ROOT/opt/intel/sgxssl/
cp   ../README.md $RPM_BUILD_ROOT/opt/intel/sgxssl/docs/
cp   License.txt $RPM_BUILD_ROOT/opt/intel/sgxssl/docs/

%files
/opt/intel/sgxssl/lib64/*
/opt/intel/sgxssl/docs/*

%files devel
/opt/intel/sgxssl/include/*

%changelog
* Thu Dec 29 2020 chenmaodong <chenmaodong@huawei.com> - 2.10-1
- init
