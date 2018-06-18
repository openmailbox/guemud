#ifndef GUEMUD_CONNECTION_H_
#define GUEMUD_CONNECTION_H_

namespace guemud {
  class Connection {
    public:
      struct Compare {
        bool operator()(const Connection& lhs, const Connection& rhs);
      };

      Connection(int socket);
      int GetSocket() const;
    private:
      int socket_;
  };
}

#endif
