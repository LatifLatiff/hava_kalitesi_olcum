#!/usr/bin/env bash
set -euo pipefail

BROKER_HOST="${1:-localhost}"
DEVICE_ID="${2:-lab-01}"
TOPIC="iot/air-quality/telemetry/${DEVICE_ID}"

mosquitto_pub -h "${BROKER_HOST}" -t "${TOPIC}" -m "$(cat examples/mqtt-payload.json)"

echo "Published to ${TOPIC} via ${BROKER_HOST}"
