#include <string>
#include <map>
#include <set>
#include <iostream>


class MobileDevice {
private:
	std::string _factory;
	std::string _model;
	std::string _mac_address;

public:
	MobileDevice(std::string factory, std::string model, std::string mac_address) : _factory(factory), _model(model), _mac_address(mac_address) {}

	std::string GetFactory() {
		return _factory;
	}

	std::string GetModel() {
		return _model;
	}

	std::string GetMacAddress() {
		return _mac_address;
	}
};


class Router {
private:
	std::string _os_name;
	std::string _os_version;
	std::string _ui_type;
	std::map<std::string, MobileDevice*> _connected_devices;

public:
	Router(std::string os_name, std::string os_version, std::string ui_type) : _os_name(os_name), _os_version(os_version), _ui_type(ui_type) {}

	std::string GetFirmware() {
		return _os_name + " " + _os_version;
	}

	std::string GetUiType() {
		return _ui_type;
	}

	void ConnectMobile(MobileDevice* mobile) {
		_connected_devices[mobile->GetMacAddress()] = mobile;
		std::cout << "Connected [" << mobile->GetMacAddress() << "]" << std::endl;
	}
};


class Firewall {
private:
	std::string _name;
	std::set<std::string> _blacklist;
	bool _is_enabled = true;

public:
	Firewall(std::string name) : _name(name) {}

	std::string GetName() {
		return _name;
	}

	void AddToBlackList(std::string ip) {
		_blacklist.insert(ip);
	}

	bool IsIpBlocked(std::string ip) {
		if (_blacklist.find(ip) != _blacklist.end()) return true;
		else return false;
	}

	void SwitchMode() {
		_is_enabled = !_is_enabled;
	}
};


class WebService {
protected:
	std::string _uri;
	std::string _host;
	std::string _ip;

public:
	WebService(std::string uri, std::string host, std::string ip) : _uri(uri), _host(host), _ip(ip) {}

	std::string GetUri() {
		return _uri;
	}

	std::string GetHost() {
		return _host;
	}

	std::string GetIp() {
		return _ip;
	}
};


class FtpService : public WebService {
private:
	std::string _username;
	std::string _password;
	bool _is_sftp;

public:
	FtpService(std::string uri, std::string host, std::string ip, bool is_sftp) : _is_sftp(is_sftp), WebService(uri, host, ip) {}

	std::string SetUsername(std::string username) {
		_username = username;
	}

	std::string SetPassword(std::string password) {
		_password = password;
	}

	void Connect() {
		if (_username != "" && _password != "") {
			if (_is_sftp) {
				std::cout << "Connect to SFTP: " << _host << std::endl;
			}
			else {
				std::cout << "Connect to FTP: " << _host << std::endl;
			}
			std::cout << "Connected!" << std::endl;
		}
		else {
			std::cout << "Required username or password " << std::endl;
		}
	}
};

void main() {
	auto mobile = MobileDevice("Xiaomi", "Mi A2", "0F:0F:0F:0F:0F");
	std::cout << "Mobile device: " << std::endl;
	std::cout << "Factory: " << mobile.GetFactory() << std::endl;
	std::cout << "Model: " << mobile.GetModel() << std::endl;
	std::cout << "Mac: " << mobile.GetMacAddress() << std::endl;
	std::cout << "\n======\n" << std::endl;

	auto router = Router("OpenWRT", "19.2", "ssh");
	std::cout << "Firmware: " << router.GetFirmware() << std::endl;
	std::cout << "UI: " << router.GetUiType() << std::endl;
	std::cout << "Connect mobile [" << mobile.GetMacAddress() << "]:" << std::endl;
	router.ConnectMobile(&mobile);
	std::cout << "\n======\n" << std::endl;

	auto firewall = Firewall("apf");
	std::cout << "Firewall name: " << firewall.GetName() << std::endl;
	std::cout << "Add to black list \"127.0.0.1\": " << std::endl;
	firewall.AddToBlackList("127.0.0.1");
	std::cout << "Is host \"10.2.3.9 blocked?\": " << std::boolalpha << firewall.IsIpBlocked("10.2.3.9") << std::endl;
	std::cout << "Is host \"127.0.0.1 blocked?\": " << std::boolalpha << firewall.IsIpBlocked("127.0.0.1") << std::endl;
	std::cout << "Switch firewall mode..." << std::endl;
	firewall.SwitchMode();
	std::cout << "Is host \"127.0.0.1 blocked?\": " << std::boolalpha << firewall.IsIpBlocked("127.0.0.1") << std::endl;
	std::cout << "\n======\n" << std::endl;

	auto service = WebService("http://localhost", "localhost", "127.0.0.1");
	std::cout << "Uri: " << service.GetUri() << std::endl;
	std::cout << "Host: " << service.GetHost() << std::endl;
	std::cout << "IP:" << service.GetIp() << std::endl;
	std::cout << "\n======\n" << std::endl;

	auto ftp = FtpService("http://localhost", "localhost", "127.0.0.1", false);
	std::cout << "Uri: " << ftp.GetUri() << std::endl;
	std::cout << "Host: " << ftp.GetHost() << std::endl;
	std::cout << "IP:" << ftp.GetIp() << std::endl;
	ftp.Connect();
	std::cout << "\n======\n" << std::endl;
}