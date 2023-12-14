#pragma once
#include "Engine/Utilities/Log.h"
#include <dxcapi.h>
#include <wrl.h>
#pragma comment(lib,"dxcompiler.lib")

class ShaderCompiler {
public:
	//ディレクトリパス
	static const std::wstring& kBaseDirectory;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// シェーダー読み込み
	/// </summary>
	/// <param name="filePath"></param>
	/// <param name="profile"></param>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<IDxcBlob> CompileShader(const std::wstring& filePath, const wchar_t* profile);

private:
	//DXC
	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils_;

	Microsoft::WRL::ComPtr<IDxcCompiler3> dxcCompiler_;

	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHandler_;
};

