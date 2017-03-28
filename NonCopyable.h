#ifndef _COMMON_NONCOPYABLE_H
#define _COMMON_NONCOPYABLE_H

/*不可复制类，保证不能通过对象不被复制*/
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

