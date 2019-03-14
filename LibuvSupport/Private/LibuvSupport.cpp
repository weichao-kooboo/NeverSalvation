#include "LibuvSupportPrivatePCH.h"
#include "LibuvSupport/Public/LibuvSupport.h"

class FLibuvSupport :public ILibuvSupport {
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FLibuvSupport,LibuvSupport)
void FLibuvSupport::StartupModule(){
	int k = 0;
}
void FLibuvSupport::ShutdownModule(){

	int k = 0;
}