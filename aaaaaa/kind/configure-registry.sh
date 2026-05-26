#!/bin/evn bash

REGISTRY_DIR="/etc/containerd/certs.d/localhost:5000"

for node in $(kind get nodes); do
  docker exec "${node}" mkdir -p "${REGISTRY_DIR}"
  cat <<EOF | docker exec -i "${node}" cp /dev/stdin "${REGISTRY_DIR}/hosts.toml"
[host."http://kind-registry:5000"]
EOF
done

