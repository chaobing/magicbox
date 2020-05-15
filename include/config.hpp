#include "common.hpp"
#include "util.hpp"
#include "version.hpp"

enum DumpType {
  DumpNone = 0,
  DumpA = 1,
  DumpB = (1 << 1),
  DumpC = (1 << 2),
};

class MagicCfg {
public:
  MagicCfg()
      : output_dir_("./log"), dump_(DumpNone),
        magic_version_(MAGIC_VERSION_NUMBER) {}
  ~MagicCfg(){};
  static MagicCfg *Instance() {
    static MagicCfg g_config;
    return &g_config;
  }

public:
  void set_output_dir(string dir) {
    CHECK(dir != "");
    output_dir_ = dir;
  }
  void set_dump_flag(int dump) { dump_ = dump; }

public:
  string output_dir() const { return output_dir_; }
  int dump_flag() const { return dump_; }
  string magic_version_string() const {
    return version_string() + MAGIC_COPYRIGHT_STRING(MAGIC_BUILD_YEAR);
  }
  string tag() const {
    string tag = "";
    tag += "MAGIC Git Tag Information\n";
    tag += "Relase branch    :" + string(MAGIC_TAG_branch) + "\n";
    tag += "Commit id        :" + string(MAGIC_TAG_commit_id) + "\n";
    tag += "Commit date      :" + string(MAGIC_TAG_commit_date) + "\n";
    return tag;
  }

  bool parse_dump_flag(const char *opt_arg) {
    static unordered_map<string, uint32_t> dump_map = {
        {"A", DumpType::DumpA},
        {"B", DumpType::DumpB},
        {"C", DumpType::DumpC},
        {"all", DumpType::DumpA | DumpType::DumpB | DumpType::DumpC},
    };
    if (!opt_arg)
      return false;
    string opt_arg_string(opt_arg);
    auto dump_types = Util::Split(opt_arg_string, ",");
    if (dump_types.size() <= 0)
      return false;
    for (auto &type : dump_types) {
      if (dump_map.find(type) == dump_map.end())
        return false;
      dump_ |= dump_map[type];
    }
    return true;
  }

private:
  int versionnum2str(int ver_num, char *buff, int size) const {
    CHECK(size > 0);
    int nlen = snprintf(buff, size, "magicbox version v");
    CHECK(nlen < size);
    int major = MAGIC_MAJOR_NUMBER(ver_num);
    int minor = MAGIC_MINOR_NUMBER(ver_num);
    nlen += snprintf(buff + nlen, size - nlen, "%d.%02d\nBranch %s", major,
                     minor, MAGIC_TAG_branch);
    CHECK(nlen <= size);
    return nlen;
  }
  string version_string() const {
    char buf[256];
    int size = 256, nlen = 0;
    nlen = versionnum2str(magic_version_, buf, size);
    nlen += snprintf(buf + nlen, size - nlen, "\nBuild label: %s %s\n",
                     __DATE__, __TIME__);
    CHECK(nlen <= size);
    return buf;
  }

private:
  string output_dir_;
  int magic_version_;
  int dump_;
};
