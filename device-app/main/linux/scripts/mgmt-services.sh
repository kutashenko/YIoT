#!/bin/bash

set -e

PARAM_SERVICE="${1}"
PARAM_COMMAND="${2}"

systemctl "${PARAM_COMMAND}" "${PARAM_SERVICE}"
