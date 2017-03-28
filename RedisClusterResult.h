#ifndef _DB_REDIS_CLUSTER_RESULT_H
#define _DB_REDIS_CLUSTER_RESULT_H
class CRedisClusterResult
{
public:
	CRedisClusterResult(redisReply* rp) :_pRedisReply(rp) {};
	~CRedisClusterResult() 
	{
		freeReplyObject(_pRedisReply);
		_pRedisReply = nullptr;
	}
	redisReply* getRedisClusterResult() 
	{
		return _pRedisReply;
	}
private:
	redisReply* _pRedisReply;
	CRedisClusterResult(const CRedisClusterResult& copy);
	const CRedisClusterResult& operator=(const CRedisClusterResult& copy);
};
#endif
