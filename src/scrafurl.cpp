/*
 * SPDX-FileCopyrightText: 2022 Andrea Pappacoda
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <scrafurl.hpp>
#include <cstdlib> /* std::atexit */

// Must define static class members in cpp units
std::once_flag Scrafurl::_isCurlInitialised;

Scrafurl::Scrafurl() {
	std::call_once(_isCurlInitialised, []() noexcept {
		curl_global_init(CURL_GLOBAL_NOTHING);
		std::atexit(curl_global_cleanup);
	});
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_responseBody);
	curl_easy_setopt(curl, CURLOPT_TCP_FASTOPEN, 1L);
	curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
	curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
	curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "http");
	_responseBody.reserve(CURL_MAX_WRITE_SIZE);
}

Scrafurl::~Scrafurl() {
	curl_easy_cleanup(curl);
}

[[nodiscard]] long Scrafurl::getResponseCode() const noexcept {
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &_responseCode);
	return _responseCode;
}

[[nodiscard]] const std::string& Scrafurl::getResponseBody() const noexcept {
	return _responseBody;
}

std::size_t Scrafurl::writeData(char* const incomingBuffer, const std::size_t size, const std::size_t count, std::string* data) {
	data->append(incomingBuffer, size * count);
	return size * count;
}
