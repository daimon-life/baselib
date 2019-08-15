/*******************************************************************************
* 文  件: RetDefine.h 
* 作  者: Robb
* 创  建: 2019年08月
* 版  权: CopyRight(C) 2019 364886923@qq.com. All rights reserved.
* 描  述: 返回值、错误码定义文件
********************************************************************************/

#pragma once

#ifndef _RET_DEFINE_H_
#define _RET_DEFINE_H_


typedef enum
{
	emRC_OK = 0,				// 正常
	emRC_PARAM_ERR,				// 参数错误
	emRC_INIT_ERR,				// 初始化错误
	emRC_INITED_ERR,			// 已经初始化
	emRC_UNINIT_ERR,			// 反初始化错误
	emRC_SOCK_ERR,				// SOCK错误或者异常
	emRC_ADDR_ERR,				// IP地址错误
	emRC_PORT_ERR,				// 端口错误
	emRC_SOCK_CREATE_ERR,		// 创建SOCK错误
	emRC_SOCK_BIND_ERR,			// 绑定SOCK错误
	emRC_SOCK_CNNT_ERR,			// 连接SOCK错误
	emRC_SOCK_LISTEN_ERR,		// 监听SOCK错误
	emRC_SOCK_ACCEPT_ERR,		// 接收SOCK连接错误
	emRC_SOCK_SEND_ERR,			// sock发送数据错误
	emRC_SOCK_RECV_ERR,			// sock接收数据错误
	emRC_SIZE_NOTENOUGH,		// 空间或大小不够
	emRC_SIZE_ENOUGH,			// 空间或大小足够了
	emRC_MSG_ERR,				// 指令错误
	emRC_CURL_ERR,				// Curl库错误
	emRC_CURL_INIT_ERR,			// CURL库初始化失败
	emRC_CURL_SEND_ERR,			// CURL库发送失败
	emRC_CURL_RECV_ERR,			// CURL库接收失败
	emRC_FILE_ERR,				// 文件错误或异常
	emRC_FILE_EXIST_ERR,		// 文件已存在
	emRC_FILE_NOTEXIST_ERR,		// 文件不存在
	emRC_FILE_HAVE_OPEN,		// 文件已经打开
	emRC_FILE_CREATE_ERR,		// 创建文件错误
	emRC_FILE_OPEN_ERR,			// 打开文件错误	
	emRC_FILE_READ_ERR,			// 读文件错误
	emRC_FILE_READ_END,			// 读到文件结尾
	emRC_FILE_WRITE_ERR,		// 写文件错误
	emRC_FILE_SEEK_ERR,			// 文件seek错误
	emRC_FILE_CLOSE_ERR,		// 关闭文件错误
	emRC_FILE_COPY_ERR,			// 复制文件错误
	emRC_FILE_CUT_ERR,			// 剪切文件错误	
	emRC_FILE_FORMAT_ERR,		// 文件格式错误
	emRC_FILE_SAME_ERR,			// 操作或对象重复
	emRC_FILE_ACCESS_ERR,		// 文件无法访问
	emRC_FILE_SIZE_ERR,			// 大小尺寸不对
	emRC_FILE_FIND_ERR,			// 查找失败
    emRC_FILE_REMOVE_ERR,       // 删除文件错误
	emRC_DIR_ERR,				// 目录错误或异常
	emRC_DIR_EXIST_ERR,			// 目录已存在
	emRC_DIR_NOTEXIST_ERR,		// 目录不存在
	emRC_DIR_CREATE_ERR,		// 创建目录错误
	emRC_DIR_OPEN_ERR,			// 打开目录错误	
	emRC_DIR_CLOSE_ERR,			// 关闭目录错误
	emRC_DIR_COPY_ERR,			// 复制目录错误
	emRC_DIR_CUT_ERR,			// 剪切目录错误
	emRC_DIR_FIND_ERR,			// 查找目录错误	
	emRC_DIR_SAME_ERR,			// 目录重名
	emRC_DIR_ACCESS_ERR,		// 目录无法访问
    emRC_DIR_REMOVE_ERR,        // 删除目录错误
	emRC_MEMROY_ERR,			// 内存错误或异常 
	emRC_MEMROY_ALLOC_ERR,		// 内存分配错误 
	emRC_MEMROY_FREE_ERR,		// 内存释放错误 
	emRC_MEMROY_OUT_ERR,		// 内存大小不够
	emRC_STREAM_ERR,			// 流错误(文件流、数据流等)
	emRC_STREAM_NOT_ERR,		// 不存在这个流
	emRC_STREAM_EXIST_ERR,		// 已存在这个流
	emRC_LIST_ERR,				// 列表错误
	emRC_QUEUE_ERR,				// 队列错误
	emRC_QUEUE_NODE_ERR,		// 队列中节点错误
	emRC_QUEUE_EMPTY_ERR,		// 队列空
	emRC_QUEUE_FULL_ERR,		// 队列满
	emRC_QUEUE_FIND_ERR,		// 查找节点失败
	emRC_XML_ERR,				// xml错误
	emRC_XML_OPEN_ERR,			// 打开xml文件失败
	emRC_XML_NODE_ERR,			// 获取XML节点内容失败
	emRC_XML_ATTRIBUTE_ERR,		// 获取XML节点属性内容失败
	emRC_XML_NODE_NOTEXIST,		// XML节点不存在
	emRC_RECORD_ERR,			// 录制错误
	emRC_RECORD_RUN_ERR,		// 录制进行中
	emRC_RECORD_NOTSTART,		// 录制已结束、或者录制未开始	
	emRC_RECORD_STOP_ERR,		// 录制停止失败
	emRC_RECORD_DIRCET_ERR,		// 启动电影模式录制失败
	emRC_RECORD_RES_ERR,		// 启动资源模式录制失败
	emRC_VA_CHECK_ERR,          // va函数调用失败
	emRC_VA_PROFILE_ERR,        // 不支持这种profile
	emRC_VA_RC_ERR,		        // 不支持这种码率控制模式
	emRC_VA_ADMIXING,           // 合成模式中，不支持同时编解码
	emRC_ENC_SUPPORT_ERR,       // 不支持编码
	emRC_ENC_ERR,			    // 编码失败
	emRC_ENC_INITED_ERR,		// 编码器初始化失败
	emRC_ENC_NOTFIND_ERR,		// 找不到编码器
	emRC_ENC_UNINIT_ERR,		// 编码器未初始化
	emRC_PARSE_ERR,				// 解析失败
	emRC_DEC_SUPPORT_ERR,       // 不支持解码
	emRC_DEC_SUPPORT_YUV420,    // 不支持解码成yuv420
	emRC_DEC_NOTFIND_ENTRYPOINT,// 找不到入口点
	emRC_DEC_FAILED,            // 解码失败
	emRC_OP_NOT_SUPPORT,		// 操作不被支持
	emRC_YUV_FORMAT_ERR,		// 不支持的YUV格式
	emRC_IDENRITY_ERR,			// 身份ID错误
	emRC_TIMEOUT,				// 超时错误
    emRC_NOTOBJECT_ERR,         // 找不到对象
    emRC_OBJECT_SUPPORT_ERR,    // 对象不支持此功能
    emRC_DATA_ERR,              // 数据错误(非法数据)
    emRC_ZLIB_ERR,              // zlib库错误
    emRC_NOTLOGIN_ERR,          // 没有登陆
    emRC_RELOGINED_ERR,         // 不能重复登陆了
    emRC_STATE_ERR,             // 状态不对
    emRC_THREAD_ERR,            // 线程错误
	emRC_CAMCTRL_ERR,			// 远摇摄像头失败
    emRC_ACCESS_ERR,            // 拒绝访问
    emRC_USER_PASSWORD_ERR,     // 用户名或密码错误
    emRC_NOT_LOGIN_INFO,        // 未设置登陆信息
	emRC_DOMAIN_PARSE_ERR,		// 域名无法解析
	emRC_SESSION_INVALID,		// 会话失效
	emRC_404_NOTFOUND,			// 404没找到


	emRC_UNKNOW = 1000			// 未知错误
}E_RetCode, E_ErrCode;


#endif // _RET_DEFINE_H_
