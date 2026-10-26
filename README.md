# AdWangMaiSDK-SPM

AdWangMaiSDK 与爱奇艺、Funtee、趣盟、Sigmob 四家适配器的 Swift Package Manager 二进制接入包。

SDK 业务版本：`8.1.0.1`；SPM 发布版本：`0.1.1`，对应仓库 tag `0.1.1`。

## Xcode 接入

1. 在 Xcode 的 GitHub 账户中使用有权访问本私有仓库的账号。
2. 通过 Add Package Dependencies 添加 `https://github.com/jerryyang007/AdWangMaiSDK-SPM.git`，依赖规则选择 Exact Version（精确版本），填写 `0.1.1`。
3. 为 App Target 选择 `AdWangMaiSDK` 和实际使用的适配器产品：

| 平台 | 产品 |
| --- | --- |
| 爱奇艺 | `XAdIQYAdSDK` |
| Funtee | `XAdFunteeSDKAd` |
| 趣盟 | `XAdQMAd` |
| Sigmob | `XAdSigmobAd` |

4. 找到 Xcode 拉取的本包目录（通常在 DerivedData 下的 `SourcePackages/checkouts`），执行一次集成命令：

```bash
python3 /absolute/path/AdWangMaiSDK-SPM/Tools/integrate.py \
  --project /absolute/path/App.xcodeproj \
  --target App \
  --adapters XAdIQYAdSDK XAdFunteeSDKAd XAdQMAd XAdSigmobAd
```

`--adapters` 与实际添加的产品保持一致；仅主 SDK 时省略该参数。多个 App Target 分别执行。之后构建自动添加自有及厂商资源，并启用 `-ObjC`，无需手动拖入 bundle。增删适配器或更新包后重跑集成命令；重复执行不会叠加阶段。

## Package.swift 接入

在宿主依赖中固定版本：

```swift
.package(url: "https://github.com/jerryyang007/AdWangMaiSDK-SPM.git", .exact("0.1.0"))
```

随后为宿主 Target 添加所需 `.product`；主 SDK 产品名为 `AdWangMaiSDK`，适配器产品名见上表。资源集成命令仍需执行一次。私有仓库拉取使用宿主配置的 GitHub 访问凭据，不把 Token 写入 URL 或 `Package.swift`。

## 业务引用

```objc
#import <AdWangMaiSDK/AdWangMaiSDK.h>
```

```swift
import AdWangMaiSDK
```

主 SDK 包含唯一 BaseSDK 实现。包内仅公开原有业务接口和模型，不包含 BaseSDK 内部头、桥接协议或适配器实现类头。不要再链接旧版主 SDK、独立 BaseSDK 或相同厂商 SDK。

## 平台与资源

主 SDK 支持真机 arm64、模拟器 arm64/x86_64；四家适配器沿用当前厂商制品能力，支持真机 arm64、模拟器 x86_64。四家组合在 Apple Silicon 上需可运行 x86_64 的模拟器环境，不能把该组合当作 arm64 模拟器产品。

自有和厂商 bundle 自动复制到 App 根目录，保持旧 SDK 的资源查找路径。独立隐私 bundle 避免覆盖 App 自己的隐私清单。静态厂商 Framework 的内嵌资源已纳入自动复制，动态 Framework 保持自己的资源。脚本保持 Xcode 用户脚本沙箱开启，冲突明确报错，复制中断可重试。

## 验证范围

主 SDK 的 Objective-C/Swift 模拟器宿主已运行，模型、图片和隐私资源读取通过。四家组合的 arm64 无签名 App 与 x86_64 模拟器 App 已编译链接；自动资源的增删恢复已验证。尚未执行四家真机广告展示验证。包中不包含开发工程、内部构建日志和本机路径报告。
