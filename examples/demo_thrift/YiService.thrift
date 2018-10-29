# thrift接口描述文件
#
# 功能: 此服务提供服务器名称、系统时间等
#
# 应用: 使用thrift --gen ${开发语言} ${thrift接口描述文件}
#       生成对应语言的接口文件，如:
#       $ thrift --gen cpp YiService.thrift

namespace cpp yisrv
 
service YiService {
	i32 GetServerName()
	i32 GetServerTime()
}