Name:           _touch
Version:        1.0.0
Release:        1%{?dist}
Summary:        A simple file creation utility written in C

License:        MIT
URL:            https://github.com/YOUR_USERNAME/_touch
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc

%description
A simple file creation utility written in C.

%prep
%setup -q

%build
gcc -Wall -Wextra -O2 -o _touch src/_touch.c

%install
mkdir -p %{buildroot}/usr/bin
install -m 755 _touch %{buildroot}/usr/bin/_touch

%files
/usr/bin/_touch

%changelog
* Fri Oct 02 2026 Your Name <your@email.com> - 1.0.0-1
- Initial RPM package