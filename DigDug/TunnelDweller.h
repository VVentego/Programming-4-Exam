#ifndef TUNNELDWELLER
#define TUNNELDWELLER
class TunnelDweller
{
public:
    TunnelDweller() = default;
    virtual ~TunnelDweller() = default;
    TunnelDweller(const TunnelDweller& other) = delete;
    TunnelDweller(TunnelDweller&& other) = delete;
    TunnelDweller& operator=(const TunnelDweller& other) = delete;
    TunnelDweller& operator=(TunnelDweller&& other) = delete;

	virtual void TunnelCollisionCallback() {};
};
#endif // !TUNNELDWELLER