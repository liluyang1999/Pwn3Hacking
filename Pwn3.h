#ifdef PWN3_EXPORTS
#define PWN3_API __declspec(dllexport)
#else
#define PWN3_API __declspec(dllimport)
#endif

class PWN3_API CPwn3 {
public:
	CPwn3(void);
};

extern PWN3_API int nPwn3;

PWN3_API int fnPwn3(void);
