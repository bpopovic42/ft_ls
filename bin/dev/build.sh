#!/usr/bin/env bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)

docker build - < Dockerfiles/Dockerfile.dev -t ${PROJECT_NAME}-dev
