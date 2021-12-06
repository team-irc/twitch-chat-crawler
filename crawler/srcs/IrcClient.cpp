#include "IrcClient.hpp"
#include "utils.hpp"


/*
	@brief connect to twitch server socket when construct client
*/
IrcClient::IrcClient()
{
	const char	*DB_HOST = std::getenv("DB_HOST");
	const char	*DB_USER = std::getenv("DB_USER");
	const char	*DB_PASS = std::getenv("DB_PASSWORD");
	const char	*DB_NAME = std::getenv("DB_NAME");
	char	sql[1024];

	_socket = new IrcSocket();

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("db:3306", DB_USER, DB_PASSWORD);
	
	stmt = con->createStatement();
	stmt->execute("CREATE DATABASE twchat IF NOT EXISTS;");
	stmt->execute("USE twchat;");
	
	stmt->execute(sql);
	// mysql_init(_connection);
	// _conn = mysql_real_connect(_connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	delete stmt;
	delete con;
	// if (mysql_query(_conn, sql) != 0)
	// 	throw (IrcError("mysql query error"));
	std::cout << "IRC Client Constructed." << std::endl;
}

IrcClient::~IrcClient()
{
	// mysql_close(_conn);
	std::cout << "IRC Client Destructed." << std::endl;
}

/*
	@brief 트위치 계정으로 채팅 서버에 로그인
*/
void	IrcClient::login_twitch()
{
	std::string	id;
	std::string	code;

	std::cout << "twitch id: ";
	std::cin >> id;
	std::cout << "twitch oauth code(https://twitchapps.com/tmi): ";
	std::cin >> code;
	_socket->connect_to_twitch_irc_server();
	code = "pass " + code;
	id = "nick " + id;
	send_to_server(code);
	send_to_server(id);
}

/*
	@brief 채팅 서버로 메세지 전송
	@detail 서버로 보내는 메세지의 끝은 "\n" 을 추가해서 알린다 (IRC RFC)
*/
void	IrcClient::send_to_server(const std::string &msg)
{
	return _socket->send_msg((msg + "\n").c_str());
}

/*
	@brief 서버로 부터 메세지를 받아와서 출력한다.
	@todo	코드 이해가 필요한 부분
*/
void	IrcClient::recv_from_server()
{
	std::string buffer = _socket->recv_msg();
	std::string line;
	std::istringstream iss(buffer);
	t_chat			chat;
	char				sql[1024];

	while (std::getline(iss, line))
	{
		if (line.find("\r") != std::string::npos)
			line = line.substr(0, line.size() - 1);
		chat = parse_chat(line);
		std::cout << "#" << chat.channel << " @" << chat.id << " : " << chat.content << std::endl;
		
	}
}

std::string		parse_id(const std::string &msg)
{
	size_t	idx;
	
	idx = msg.find_first_of('!', 0);
	if (idx == std::string::npos)
		throw (IrcError("parse_nick error | " + msg));
	return (msg.substr(1, idx - 1));
}

std::string		parse_channel(const std::string &msg)
{
	size_t	idx;
	size_t	idx_end;

	idx = msg.find_first_of('#', 0);
	if (idx == std::string::npos)
		throw (IrcError("parse_channel error | " + msg));
	idx_end = msg.find_first_of(' ', idx);
	if (idx_end == std::string::npos)
		throw (IrcError("parse_channel ' ' not found error | " + msg));
	return (msg.substr(idx + 1, idx_end - (idx + 1)));
}

std::string		parse_content(const std::string &msg)
{
	size_t	idx;

	idx = msg.find_first_of(':', 1);
	if (idx == std::string::npos)
		throw (IrcError("parse_content ':' not found error | " + msg));
	return (msg.substr(idx + 1, msg.length() - (idx + 1)));
}

/*
	@brief parse message to nick, content
*/
t_chat	IrcClient::parse_chat(const std::string &msg)
{
	t_chat	chat;

	try
	{
		chat.id = parse_id(msg);
		chat.channel = parse_channel(msg);
		chat.content = parse_content(msg);
	}
	catch (IrcError const &e)
	{
		std::cerr << "[-] ";
		std::cerr << e.what() << std::endl;
		chat.id = "error";
		chat.channel = "error";
		chat.content = "error";
	}
	return (chat);
}
