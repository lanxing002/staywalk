import logging

logging.basicConfig(
    level=logging.DEBUG,  # 设置日志级别
    format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",  # 设置日志格式
    datefmt="%Y-%m-%d %H:%M:%S",  # 设置日期时间格式
    # filename="app.log",  # 指定日志文件（不指定则输出到控制台）
    # filemode="a"  # 文件模式 'a' 表示追加模式，'w' 表示覆盖模式
)
