#define T_DIR     1   // Directory
#define T_FILE    2   // File
#define T_DEVICE  3   // Device

// 文件系统的结构
// dev->int:文件系统磁盘设备
// ino->uint: Inode number
// type->short:文件类型
// nlink->short:文件链接link的数量
// size->uint64:文件字节数
struct stat {
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short type;  // Type of file
  short nlink; // Number of links to file
  uint64 size; // Size of file in bytes
};
