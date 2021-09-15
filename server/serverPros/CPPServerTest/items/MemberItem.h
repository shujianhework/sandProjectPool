#pragma once
struct MemberItem
{
private:
	enum MemberItemState
	{
		INVALUE = 0,
		WAIT_DELETE,
		DELETE,
		USER,
	};
public:
	unsigned char memFlg;
	unsigned short ref;
	unsigned int size;
	MemberItem():memFlg(1),ref(0),size(0) {
	}
	bool retain();
	void release();
};

