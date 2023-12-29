#!/bin/bash

package_cloud push cogo152/gproject/ubuntu/jammy package/gctest-core_1.0.8_arm.deb
package_cloud push cogo152/gproject/ubuntu/jammy package/gctest-core_1.0.8_arm64.deb
package_cloud push cogo152/gproject/ubuntu/jammy package/gctest-core_1.0.8_amd64.deb

package_cloud push cogo152/gproject/el/8 package/gctest-core-1.0.8-1.x86_64.rpm
