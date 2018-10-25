
-- 全局变量
id = 666
title = "this is a test"
array = {r = 2,g = 3,b = 4}
array_1d = {2,5,26,8}
array_2d = {{2,5},{15,18},{25,26,28},{0,5,4}}

-- 无参函数
function ruler_func()
    print("[lua]: this is some thing need to tell you!!!");
end

-- 有参函数
function add_func(a,b)
    print("[lua]: a("..a..") + b("..b..") ="..a+b.."!");
    return a+b;
end