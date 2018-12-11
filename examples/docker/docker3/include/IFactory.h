#ifndef _YI_FACTORY_H_
#define _YI_FACTORY_H_

//windows
//1、在文件里面最前面加上：#define DLL_PUBLIC  __attribute__((visibility("default")))
//2、在文件里面需要导出的函数前加上：extern "C" DLL_PUBLIC
//3、Linux下动态库（so）编译时默认不导出，在Makefile中需要添加： - fvisibility = hidden
//#define DLL_EXPORT_C extern "C" __attribute__ ((visibility("default")))

// 对象接口
struct IMath
{
	virtual ~IMath() = 0;
	virtual double add(double a, double b) = 0;//加法
	virtual double sub(double a, double b) = 0;//减法
	virtual double mul(double a, double b) = 0;//乘法
	virtual double div(double a, double b) = 0;//除法
};

// 工厂接口
struct IFactory
{
	virtual ~IFactory();
	virtual IMath* create_math();
	virtual void destroy_math(IMath *math);
};

// 导出函数
extern "C"
{
	IFactory* create_factory();
	void destroy_factory(IFactory* factory);
}

#endif //_YI_FACTORY_H_