#pragma once
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str, char d);

void IpFilter();
void SortIp(std::vector<std::vector<std::string>>& ip_pool);
bool IsFirstEqualOne(const std::vector<std::string>& ip);
