// 存储系统运行的信息，freemem->内存有多少空余字节,nproc->UNUSED进程数目
struct sysinfo {
  uint64 freemem;   // amount of free memory (bytes)
  uint64 nproc;     // number of process
};
