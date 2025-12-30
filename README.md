wordui/  
├── Controller/                    # 控制器层  
│   ├── applicationController.cpp/h       # 主控制器  
│   ├── loginController.cpp/h             # 登录控制器  
│   ├── enrollController.cpp/h            # 注册控制器  
│   ├── userSpaceController.cpp/h         # 用户空间控制器  
│   ├── changePwdController.cpp/h         # 修改密码控制器  
│   ├── studyCenterController.cpp/h       # 学习中心控制器  
│   ├── studyWordController.cpp/h         # 单词学习控制器  
│   ├── reviewController.cpp/h            # 复习控制器  
│   ├── newWordController.cpp/h           # 生词本控制器  
│   └── viewData.h                        # 视图枚举定义  
│  
├── Models/                       # 模型层  
│   ├── userModel.cpp/h                  # 用户模型  
│   ├── wordModel.cpp/h                  # 单词模型  
│   ├── databaseManager.cpp/h            # 数据库管理器  
│   └── appdata.h                        # 应用数据定义  
│  
├── View/                         # 视图层  
│   ├── mywidght.cpp/h                   # 自定义窗口基类  
│   ├── login.cpp/h                      # 登录窗口  
│   ├── enroll.cpp/h                     # 注册窗口  
│   ├── userSpace.cpp/h                  # 用户空间  
│   ├── changePwd.cpp/h                  # 修改密码窗口  
│   ├── studyCenter.cpp/h                # 学习中心  
│   ├── studyWord.cpp/h                  # 单词学习界面  
│   ├── review.cpp/h                     # 复习界面  
│   └── newWord.cpp/h                    # 生词本界面  
│  
├── UI/                           # UI 文件  
│   ├── login.ui                         # 登录界面  
│   ├── enroll.ui                        # 注册界面  
│   ├── userSpace.ui                     # 用户空间界面  
│   ├── changePwd.ui                     # 修改密码界面  
│   ├── studyCenter.ui                   # 学习中心界面  
│   ├── studyWord.ui                     # 单词学习界面  
│   ├── review.ui                        # 复习界面  
│   └── newWord.ui                       # 生词本界面  
│  
├── Resources/                    # 资源文件  
│   ├── pic.qrc                           # 图片资源  
│   └── qss.qrc                           # 样式表资源  
│  
├── main.cpp                     # 主程序入口  
└── wordui.pro                   # Qt 项目文件  
