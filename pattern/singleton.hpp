
class SingleTon {
public:
    static SingleTon* getInstance() {
        if (pinstance_ == nullptr) {
            lock();
            if (pinstance_ == nullptr) {
                pinstance_ = new SingleTon();
            }
            unlock();
        }
        return pinstance_;
    }
private:
    SingleTon();
    SingleTon(const SingleTon &rsc) = delete;
    SingleTon &operator=(const SingleTon &rsc) = delete;
    SingleTon(SingleTon &&rsc) = delete;
    SingleTon &operator=(SingleTon &&rsc) = delete;
    static SingleTon *pinstance_;
};

SingleTon* SingleTon::pinstance_ = nullptr;