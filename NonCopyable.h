#ifndef _COMMON_NONCOPYABLE_H
#define _COMMON_NONCOPYABLE_H

/*���ɸ����࣬��֤����ͨ�����󲻱�����*/
class CNonCopyable 
{
private:
	CNonCopyable(const CNonCopyable& copy);
	const CNonCopyable& operator=(const CNonCopyable& copy);

protected:
	CNonCopyable() {}
	~CNonCopyable() {}
};
#endif // !_COMMON_NONCOPYABLE_H

