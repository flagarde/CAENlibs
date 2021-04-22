#########################################################
#            CMakeLists.txt to build CAENlibs           #
#                @author LAGARDE Francois               #
#########################################################

cmake_minimum_required(VERSION 3.15)

project(CAENlibs VERSION "1.0.0.0" DESCRIPTION "CAEN libraries" HOMEPAGE_URL "https://www.caen.it/subfamilies/software-libraries/" LANGUAGES C CXX)

include(GNUInstallDirs)

add_subdirectory(CAENVME)

add_subdirectory(CAENComm)

add_subdirectory(CAENHV)

add_subdirectory(CAENDigitizer)

add_subdirectory(CAENDPP)
