@echo off

pushd ..
cd third_part
echo Start clone third part
if not exist imgui (git clone git@github.com:yuuKiwAw/imgui.git)
if not exist glfw (git clone git@github.com:yuuKiwAw/glfw.git)
echo Complate clone third part